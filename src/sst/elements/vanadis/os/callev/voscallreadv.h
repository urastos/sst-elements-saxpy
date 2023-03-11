// Copyright 2009-2022 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2022, NTESS
// All rights reserved.
//
// Portions are copyright of other developers:
// See the file CONTRIBUTORS.TXT in the top level directory
// the distribution for more information.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef _H_VANADIS_SYSCALL_READV
#define _H_VANADIS_SYSCALL_READV

#include "os/voscallev.h"

namespace SST {
namespace Vanadis {

class VanadisSyscallReadvEvent : public VanadisSyscallEvent {
public:
    VanadisSyscallReadvEvent() : VanadisSyscallEvent() {}
    VanadisSyscallReadvEvent(uint32_t core, uint32_t thr, VanadisOSBitType bittype, int64_t fd, uint64_t iovec_addr, int64_t iovec_count)
        : VanadisSyscallEvent(core, thr, bittype), readv_fd(fd), readv_iovec_addr(iovec_addr), readv_iov_count(iovec_count) {}

    VanadisSyscallOp getOperation() { return SYSCALL_OP_READV; }

    int64_t getFileDescriptor() const { return readv_fd; }
    uint64_t getIOVecAddress() const { return readv_iovec_addr; }
    int64_t getIOVecCount() const { return readv_iov_count; }

private:
    int64_t readv_fd;
    uint64_t readv_iovec_addr;
    int64_t readv_iov_count;
};

} // namespace Vanadis
} // namespace SST

#endif
