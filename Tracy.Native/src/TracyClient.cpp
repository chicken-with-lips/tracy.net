#include "Tracy.hpp"
////#include "common/TracyColor.hpp"
////#include "common/TracyAlign.hpp"
////#include "common/TracyForceInline.hpp"
#include "common/TracySystem.hpp"
#include "client/TracyProfiler.hpp"
#include "common/TracyQueue.hpp"
//#include "TracyC.h"

using namespace tracy;

extern "C" void tracy_FrameMark() {
    FrameMark;
}

extern "C" void tracy_ZoneScoped() {
//    ZoneScoped;
}

extern "C" void tracy_ZoneBegin() {

//    const auto srcloc = Profiler::AllocSourceLocation( 0, "xerg", "xerg2", "XERG3", 4);

    TracyQueuePrepare(QueueType::ZoneBegin);
    MemWrite( &item->zoneBegin.time, Profiler::GetTime() );
//    MemWrite( &item->zoneBegin.srcloc, srcloc );
    TracyQueueCommit(zoneBeginThread);
}

extern "C" void tracy_ZoneName( const char* name, int nameLength) {
    auto ptr = (char*)tracy_malloc( nameLength );
    memcpy( ptr, name, nameLength );

    TracyQueuePrepare( QueueType::ZoneName );
    MemWrite( &item->zoneTextFat.text, (uint64_t)ptr );
    MemWrite( &item->zoneTextFat.size, (uint16_t)nameLength );
    TracyQueueCommit( zoneTextFatThread );
}

extern "C" void tracy_ZoneEnd() {
    TracyQueuePrepare(QueueType::ZoneEnd);
    MemWrite( &item->zoneEnd.time, Profiler::GetTime() );
    TracyQueueCommit(zoneBeginThread);
}