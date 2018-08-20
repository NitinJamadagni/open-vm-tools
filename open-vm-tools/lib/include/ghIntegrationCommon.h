/*********************************************************
 * Copyright (C) 2008-2018 VMware, Inc. All rights reserved.
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

/*
 * ghIntegrationCommon.h --
 *
 *	Common data structures and definitions used by Guest/Host Integration.
 */

#ifndef _GHINTEGRATIONCOMMON_H_
#define _GHINTEGRATIONCOMMON_H_

/*
 * Common data structures and definitions used by Guest/Host Integration.
 */
#define GHI_HGFS_SHARE_URL_SCHEME_UTF8 "x-vmware-share"
#define GHI_HGFS_SHARE_URL_UTF8 "x-vmware-share://"
#define GHI_HGFS_SHARE_URL      _T(GHI_HGFS_SHARE_URL_UTF8)

/*
 * Messages over different channels will be handled by
 * different modules.
 */
#define GHI_CHANNEL_TOOLS_USER                  0  // Handled by tools module
                                                   // in local VM (TOOLS_DND_NAME guestRPC)
                                                   // or by VDPUnityMKSControl module
                                                   // in View RMKS
#define GHI_CHANNEL_TOOLS_MAIN                  1  // Handled by tools module
                                                   // in local VM (TOOLS_DAEMON_NAME guestRPC)
#define GHI_CHANNEL_VIEW_REMOTE_SHARED_FOLDER   2  // VDPSharedFolderMgrMKSControl module
                                                   // in View RMKS
#define GHI_CHANNEL_DND                         3  // DnD for both local VM and View RMKS.
#define GHI_CHANNEL_MAX                         4
typedef uint32 GHIChannelType;

#define GHI_REQUEST_SUCCESS_OK       0  // Guest returns OK.
#define GHI_REQUEST_SUCCESS_ERROR    1  // Guest returns ERROR.
#define GHI_REQUEST_GUEST_RPC_FAILED 2  // Not sent to guest
                                        // or guest failed to return,
                                        // including timeout.
#define GHI_REQUEST_GENERAL_ERROR    3  // General error, can be any
                                        // situation except
                                        // MKSCONTROL_GHI_REQUEST_SUCCESS_OK.
typedef uint32 GHIRequestResult;

/*
 * Message names - DnD.
 */
#define GHI_DND_DND_HOST_GUEST_CMD              "ghi.dnd.dnd.hostguest"
#define GHI_DND_COPYPASTE_HOST_GUEST_CMD        "ghi.dnd.copypaste.hostguest"
#define GHI_DND_HOST_SHAKEHAND_CMD              "ghi.dnd.shakehand"
#define GHI_DND_HOST_GETFILES_CMD               "ghi.dnd.host.getfiles"
#define GHI_DND_HOST_GETFILES_ANSWER_OVERWRITE  "ghi.dnd.host.getfiles.answer.overwrite"
#define GHI_DND_HOST_SENDFILES_CMD              "ghi.dnd.host.sendfiles"
#define GHI_DND_HOST_TRANSFERFILES_CANCEL_CMD   "ghi.dnd.host.transferfiles.cancel"
#define GHI_DND_HOST_ADDBLOCK_CMD               "ghi.dnd.host.addblock"
#define GHI_DND_HOST_REMOVEBLOCK_CMD            "ghi.dnd.host.removeblock"

#define GHI_DND_GUEST_RET_MAX_LEN               64
#define GHI_DND_GUEST_RET_ERROR                 "error"
#define GHI_DND_GUEST_RET_INPROGRESS            "inProgress"
#define GHI_DND_GUEST_RET_DONE                  "done"


#endif // ifndef _GHINTEGRATIONCOMMON_H_
