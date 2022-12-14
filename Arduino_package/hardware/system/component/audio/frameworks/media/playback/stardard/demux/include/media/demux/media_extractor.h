/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_MEDIA_DEMUX_MEDIA_EXTRACTOR_H
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_MEDIA_DEMUX_MEDIA_EXTRACTOR_H

#include <stdio.h>
#include <stdint.h>

#include "osal_cxx/errors.h"
#include "osal_cxx/refptr.h"

namespace ameba::media
{

class DataSourceBase;
class MetaDataBase;
class MetaData;
class MediaTrack;

class MediaExtractor;
typedef MediaExtractor *(*InitializeFunction)(DataSourceBase *source, void *meta);
typedef void (*FeleaseMetaFunction)(void *meta);

// The Detector can optionally fill in an opaque object, "meta", that helps
// the corresponding extractor initialize its state without duplicating
// effort already exerted by the Detector. If "release_meta" is given, it will be
// called against the opaque object when it is no longer used.
typedef InitializeFunction(*DetectorFunction)(
	DataSourceBase *source, float *confidence,
	void **meta, FeleaseMetaFunction *release_meta);

typedef struct {
	uint8_t b[16];
} UUID_t;

typedef struct {
	// version number of this structure
	uint32_t version;

	// A unique identifier for this extractor.
	// See below for a convenience macro to create this from a string.
	UUID_t extractor_uuid;

	// Version number of this extractor. When two extractors with the same
	// uuid are encountered, the one with the largest version number will
	// be used.
	uint32_t extractor_version;

	// a human readable name
	char *extractor_name;

	// the Detector function
	DetectorFunction detector_function;
} ExtractorType;

class MediaExtractor : public RefPtr
{
public:
	virtual ~MediaExtractor();
	virtual size_t GetTracksNum() = 0;
	virtual MediaTrack *GetTrack(size_t index) = 0;
	virtual res_t GetTrackMetaData(
		MetaDataBase &meta,
		size_t index, uint32_t flags = 0) = 0;

	// Return container specific meta-data. The default implementation
	// returns an empty metadata object.
	virtual res_t GetMetaData(MetaDataBase &meta) = 0;

	enum MediaFlags {
		CAN_REWIND_BACKWARD  = 1,  // the "rewind 10secs back button"
		CAN_REWIND_FORWARD   = 2,  // the "rewind 10secs forward button"
		CAN_PAUSE          = 4,
		CAN_REWIND           = 8,  // the "rewind bar"
	};

	// If subclasses do _not_ override this, the default is
	// CAN_REWIND_BACKWARD | CAN_REWIND_FORWARD | CAN_REWIND | CAN_PAUSE
	virtual uint32_t GetMediaFlags() const;

	virtual const char *Name()
	{
		return "<unspecified>";
	}

	static const uint32_t EXTRACTOR_TYPE_VERSION = 1;

	typedef ExtractorType(*GetExtractorType)();

	sptr<MetaData> GetMetaData();
	sptr<MetaData> GetTrackMetaData(size_t index, uint32_t flags = 0);

protected:
	MediaExtractor();

private:
	MediaExtractor(const MediaExtractor &);
	MediaExtractor &operator=(const MediaExtractor &);
};

// purposely not defined anywhere so that this will fail to link if
// expressions below are not evaluated at compile time
int InvalidUuidString(const char *);

template <typename T, size_t N>
constexpr uint8_t DigitAt(const T(&s)[N], const size_t n)
{
	return s[n] >= '0' && s[n] <= '9' ? s[n] - '0'
		   : s[n] >= 'a' && s[n] <= 'f' ? s[n] - 'a' + 10
		   : s[n] >= 'A' && s[n] <= 'F' ? s[n] - 'A' + 10
		   : InvalidUuidString("uuid: bad digits");
}

template <typename T, size_t N>
constexpr uint8_t HexByteAt(const T(&s)[N], size_t n)
{
	return (DigitAt(s, n) << 4) + DigitAt(s, n + 1);
}

constexpr bool AssertIsDash(char c)
{
	return c == '-' ? true : InvalidUuidString("Wrong format");
}

template <size_t N>
constexpr UUID_t ConstUUID(const char (&s) [N])
{
	static_assert(N == 37, "uuid: wrong length");
	return
		AssertIsDash(s[8]),
		AssertIsDash(s[13]),
		AssertIsDash(s[18]),
		AssertIsDash(s[23]),
	UUID_t {{
			HexByteAt(s, 0),
			HexByteAt(s, 2),
			HexByteAt(s, 4),
			HexByteAt(s, 6),
			HexByteAt(s, 9),
			HexByteAt(s, 11),
			HexByteAt(s, 14),
			HexByteAt(s, 16),
			HexByteAt(s, 19),
			HexByteAt(s, 21),
			HexByteAt(s, 24),
			HexByteAt(s, 26),
			HexByteAt(s, 28),
			HexByteAt(s, 30),
			HexByteAt(s, 32),
			HexByteAt(s, 34),
		}};
}
// Convenience macro to create a UUID_t from a string literal, which should
// be formatted as "12345678-1234-1234-1234-123456789abc", as generated by
// e.g. https://www.uuidgenerator.net/ or the 'uuidgen' linux command.
// Hex digits may be upper or lower case.
//
// The macro call is otherwise equivalent to specifying the structure directly
// (e.g. UUID("7d613858-5837-4a38-84c5-332d1cddee27") is the same as
//       {{0x7d, 0x61, 0x38, 0x58, 0x58, 0x37, 0x4a, 0x38,
//         0x84, 0xc5, 0x33, 0x2d, 0x1c, 0xdd, 0xee, 0x27}})

#define UUID(str) []{ constexpr UUID_t uuid = ConstUUID(str); return uuid; }()

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_MEDIA_DEMUX_MEDIA_EXTRACTOR_H
