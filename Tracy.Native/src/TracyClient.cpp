#include "Tracy.hpp"
////#include "common/TracyColor.hpp"
////#include "common/TracyAlign.hpp"
////#include "common/TracyForceInline.hpp"
#include "common/TracySystem.hpp"
#include "client/TracyProfiler.hpp"
#include "common/TracyQueue.hpp"
//#include "TracyC.h"

using namespace tracy;

#if defined(_MSC_VER)
#    define _TRACY_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
#    define _TRACY_EXPORT __attribute__((visibility("default")))
#else
#    define _TRACY_EXPORT
#    pragma warning "Unknown dynamic link import/export semantics."
#endif

#ifdef __cplusplus
#    define _TRACY_EXTERN extern "C"
#else
#    define _TRACY_EXTERN extern
#endif

#define TRACY_CAPI _TRACY_EXTERN _TRACY_EXPORT

TRACY_CAPI void tracy_FrameMark() {
    FrameMark;
}

TRACY_CAPI void tracy_ZoneScoped() {
//    ZoneScoped;
}

TRACY_CAPI void tracy_ZoneBegin() {

//    const auto srcloc = Profiler::AllocSourceLocation( 0, "xerg", "xerg2", "XERG3", 4);

    TracyQueuePrepare(QueueType::ZoneBegin);
    MemWrite( &item->zoneBegin.time, Profiler::GetTime() );
//    MemWrite( &item->zoneBegin.srcloc, srcloc );
    TracyQueueCommit(zoneBeginThread);
}

TRACY_CAPI void tracy_ZoneName( const char* name, int nameLength) {
    auto ptr = (char*)tracy_malloc( nameLength );
    memcpy( ptr, name, nameLength );

    TracyQueuePrepare( QueueType::ZoneName );
    MemWrite( &item->zoneTextFat.text, (uint64_t)ptr );
    MemWrite( &item->zoneTextFat.size, (uint16_t)nameLength );
    TracyQueueCommit( zoneTextFatThread );
}

TRACY_CAPI void tracy_ZoneEnd() {
    TracyQueuePrepare(QueueType::ZoneEnd);
    MemWrite( &item->zoneEnd.time, Profiler::GetTime() );
    TracyQueueCommit(zoneBeginThread);
}