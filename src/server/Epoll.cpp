#include"Epoll.hpp"

Epoll::Epoll()
{
    epollFd = epoll_create(MAX_EVENT_NUMBER);
}

int Epoll::getFd()
{
    return epollFd;
}

void Epoll::addFd(int fd, bool isRead, bool isET, bool isOneShot, bool isNonBlock)
{
    epoll_event event = createEvent(fd, isRead, isET, isOneShot);
    epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event);
    if (isNonBlock) {
        setNonBlocking(fd);
    }
}

void Epoll::modFd(int fd, bool isModToRead, bool isET, bool isOneShot)
{
    epoll_event event = createEvent(fd, isModToRead, isET, isOneShot);
    epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &event);
}

void Epoll::delFd(int fd)
{
    epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, 0);
}

void Epoll::appendRdwrFdFuncs(int fd, Func func)
{
    rdwrFdFuncs[fd] = func;
}

void Epoll::appendrReadFdFuncs(int fd, Func func)
{
    readFdFuncs[fd] = func;
}

void Epoll::appendrWriteFdFuncs(int fd, Func func)
{
    writeFdFuncs[fd] = func;
}

void Epoll::setComReadFunc(Func func)
{
    comReadFunc = func;
}

void Epoll::setComWriteFunc(Func func)
{
    comWriteFunc = func;
}

void Epoll::setErrDealFunc(Func func)
{
    errDealFunc = func;
}

int Epoll::eventDeal()
{
    int number = epoll_wait(epollFd, events, MAX_EVENT_NUMBER, -1);
    if (number < 0 && errno != EINTR) {
        LOG_ERROR("epoll failure");
        return -1;
    }
    for (int i = 0; i < number; i++) {
        int fd = events[i].data.fd;
        event_type ev = events[i].events;

        if (rdwrFdFuncs.count(fd)) {
            rdwrFdFuncs[fd](fd);
        } else if (ev & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
            if (errDealFunc) {
                errDealFunc(fd);
            }
            // std::cout << "EPOLLRDHUP" << std::endl;
            // errDealFunc(fd);
        } else if (readFdFuncs.count(fd) && (ev & EPOLLIN)) {
            readFdFuncs[fd](fd);
        } else if (writeFdFuncs.count(fd) && (ev & EPOLLOUT)) {
            writeFdFuncs[fd](fd);
        } else if (ev & EPOLLIN) {
            if (comReadFunc) {
                comReadFunc(fd);
            }
        } else if (ev & EPOLLOUT) {
            if (comWriteFunc) {
                comWriteFunc(fd);
            }
        }
    }
    return 0;
}

int Epoll::setNonBlocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

epoll_event Epoll::createEvent(int fd, bool isModToRead, bool isET, bool isOneShot)
{
    event_type ev = EPOLLRDHUP;
    if (isModToRead) {
        ev |= EPOLLIN;
    } else {
        ev |= EPOLLOUT;
    }
    if (isET) {
        ev |= EPOLLET;
    }
    if (isOneShot) {
        ev |= EPOLLONESHOT;
    }
    epoll_event event;
    event.data.fd = fd;
    event.events = ev;
    return event;
}