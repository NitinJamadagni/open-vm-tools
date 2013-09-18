/*********************************************************
 * Copyright (C) 2010 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation version 2.1 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the Lesser GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA.
 *
 *********************************************************/

/*********************************************************
 * The contents of this file are subject to the terms of the Common
 * Development and Distribution License (the "License") version 1.0
 * and no later version.  You may not use this file except in
 * compliance with the License.
 *
 * You can obtain a copy of the License at
 *         http://www.opensource.org/licenses/cddl1.php
 *
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 *********************************************************/

/*
 * hgfsTransport.h --
 *
 * Transport file shared between guest drivers and host.
 */

#ifndef _HGFS_TRANSPORT_H_
# define _HGFS_TRANSPORT_H_

#include "vmci_defs.h"

/************************************************
 *    VMCI specific data structures, macros     *
 ************************************************/

#define HGFS_VMCI_VERSION_1          0x1

typedef enum {
   HGFS_TS_IO_PENDING,
   HGFS_TS_IO_COMPLETE,
   HGFS_TS_IO_FAILED,
} HgfsTransportRequestState;

typedef enum {
   HGFS_ASYNC_IOREQ_SHMEM,
   HGFS_ASYNC_IOREQ_GET_PAGES,
   HGFS_ASYNC_IOREP,
} HgfsAsyncReplyFlags;

typedef enum {
   HGFS_TH_REP_GET_PAGES,
   HGFS_TH_REQUEST,
   HGFS_TH_TERMINATE_SESSION,
} HgfsTransportPacketType;

#define HGFS_VMCI_TRANSPORT_ERROR      (VMCI_ERROR_CLIENT_MIN - 1)
#define HGFS_VMCI_VERSION_MISMATCH     (VMCI_ERROR_CLIENT_MIN - 2)
#define HGFS_VMCI_TYPE_NOT_SUPPORTED   (VMCI_ERROR_CLIENT_MIN - 3)

/*
 * Used By : Guest and Host
 * Lives in : Inside HgfsVmciTransportHeader
 */

typedef
#include "vmware_pack_begin.h"
struct HgfsIov {
   uint64 pa;                 /* Physical addr */
   uint32 len;                /* length of data; should be <= PAGE_SIZE */
}
#include "vmware_pack_end.h"
HgfsIov;

/*
 * Used By : Guest and Host
 * Lives in : Inside HgfsVmciTransportHeader
 */

typedef
#include "vmware_pack_begin.h"
struct HgfsAsyncIov {
   uint64 pa;                 /* Physical addr */
   uint64 va;                 /* Virtual addr */
   uint32 len;                /* length of data; should be <= PAGE_SIZE */
   uint64 index;              /* Guest opaque data; should not be changed by
                                 host */
   Bool chain;                /* Are pages chained ? */
}
#include "vmware_pack_end.h"
HgfsAsyncIov;

/*
 * Every VMCI request will have this transport Header sent over
 * in the datagram by the Guest OS.
 *
 * Node fields are set to be compatible for backwards compatibility
 * for version 1 and common for newer versions.
 *
 * Used By : Guest and Host
 * Lives in : Sent by Guest inside VMCI datagram
 */
typedef
#include "vmware_pack_begin.h"
struct HgfsVmciHeaderNode {
   uint32 version;                          /* Version number */
   HgfsTransportPacketType pktType;         /* Type of packet */
}
#include "vmware_pack_end.h"
HgfsVmciHeaderNode;

typedef
#include "vmware_pack_begin.h"
struct HgfsVmciTransportHeader {
   HgfsVmciHeaderNode node;                 /* Node: version, type etc. */
   uint32 iovCount;                         /* Number of iovs */
   union {
      HgfsIov iov[1];                       /* (PA, len) */
      HgfsAsyncIov asyncIov[1];
   };
}
#include "vmware_pack_end.h"
HgfsVmciTransportHeader;

/*
 * Indicates status of VMCI requests. If the requests are processed sync
 * by the hgfsServer then guest should see IO_COMPLETE otherwise IO_PENDING.
 *
 * Used By: Guest and Host
 * Lives in: Guest Memory
 */
typedef
#include "vmware_pack_begin.h"
struct HgfsVmciTransportStatus {
   HgfsTransportRequestState status; /* IO_PENDING, IO_COMPLETE, IO_FAILED etc */
   uint32 size;                      /* G->H: Size of the packet,H->G: How much more space is needed */
}
#include "vmware_pack_end.h"
HgfsVmciTransportStatus;

typedef
#include "vmware_pack_begin.h"
struct HgfsVmciAsyncResponse {
   uint64 id;            /* Id corresponding to the guest request */
}
#include "vmware_pack_end.h"
HgfsVmciAsyncResponse;

typedef
#include "vmware_pack_begin.h"
struct HgfsVmciAsyncShmem {
   uint32 count;          /* Number of iovs */
   HgfsAsyncIov iov[1];
}
#include "vmware_pack_end.h"
HgfsVmciAsyncShmem;

typedef
#include "vmware_pack_begin.h"
struct HgfsVmciAsyncReply {
   uint32 version;
   HgfsAsyncReplyFlags pktType;
   union {
     HgfsVmciAsyncResponse response;
     HgfsVmciAsyncShmem shmem;
   };
}
#include "vmware_pack_end.h"
HgfsVmciAsyncReply;

#endif /* _HGFS_TRANSPORT_H_ */

