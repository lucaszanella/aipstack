/*
 * Copyright (c) 2018 Ambroz Bizjak
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AIPSTACK_EVENT_PROVIDER_LINUX_H
#define AIPSTACK_EVENT_PROVIDER_LINUX_H

#include <cstdint>

#include <sys/epoll.h>
#include <memory>

#include <aipstack/misc/NonCopyable.h>
#include <aipstack/misc/platform_specific/FileDescriptorWrapper.h>
#include <aipstack/event_loop/EventLoopCommon.h>
#include <aipstack/event_loop/EventBridge.h>


namespace AIpStack {

//class EventProviderVirtualFd;

class EventProviderVirtual :
    public EventProviderBase,
    private NonCopyable<EventProviderVirtual>
{
    friend class EventProviderVirtualFd;
    
    inline static constexpr int MaxEpollEvents = 64;

public:
    EventProviderVirtual ();

    EventProviderVirtual(std::shared_ptr<EventBridge> event_bridge);

    ~EventProviderVirtual ();

    void waitForEvents (EventLoopTime wait_time);

    bool dispatchEvents ();

    void signalToCheckAsyncSignals ();

private:
    //void control_epoll (int op, int fd, std::uint32_t events, void *data_ptr);

private:
    //FileDescriptorWrapper m_epoll_fd;
    //FileDescriptorWrapper m_timer_fd;
    //FileDescriptorWrapper m_event_fd;
    EventLoopTime m_timerfd_time;
    bool m_force_timerfd_update;
    std::shared_ptr<EventBridge> m_event_bridge;
    //int m_cur_epoll_event;
    //int m_num_epoll_events;
    //struct epoll_event m_epoll_events[MaxEpollEvents];
};
/*
class EventProviderVirtualFd :
    public EventProviderFdBase,
    private NonCopyable<EventProviderVirtualFd>
{
public:
    void initFdImpl (int fd, EventLoopFdEvents events);

    void updateEventsImpl (EventLoopFdEvents events);

    void resetImpl ();

private:
    inline EventProviderVirtual & getProvider () const;
};
*/
using EventProvider = EventProviderVirtual;
//using EventProviderFd = EventProviderVirtualFd;

#define AIPSTACK_EVENT_PROVIDER_IMPL_FILE \
    <aipstack/event_loop/platform_specific/EventProviderVirtual_impl.h>

}

#endif
