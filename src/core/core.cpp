/*
 * core.cpp
 * Copyright (C) 2010-2017 Belledonne Communications SARL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <algorithm>
#include <sstream>

#include "chat/chat-room/basic-chat-room.h"
#include "core-p.h"
#include "db/main-db.h"
#include "logger/logger.h"
#include "object/object-p.h"
#include "paths/paths.h"

// TODO: Remove me later.
#include "private.h"

#define LINPHONE_DB "linphone.db"

// =============================================================================

using namespace std;

LINPHONE_BEGIN_NAMESPACE

// -----------------------------------------------------------------------------

Core::Core (LinphoneCore *cCore) : Object(*new CorePrivate) {
	L_D();
	d->cCore = cCore;
	const char *uri = lp_config_get_string(linphone_core_get_config(d->cCore), "server", "db_uri", NULL);
	if (uri) {
		AbstractDb::Backend backend =
			strcmp(lp_config_get_string(linphone_core_get_config(d->cCore), "server", "db_backend", NULL), "mysql") == 0
			? MainDb::Mysql
			: MainDb::Sqlite3;
		lInfo() << "Creating " LINPHONE_DB " at: " << uri;
		d->mainDb.connect(backend, uri);
		return;
	}

	static string path = getDataPath() + "/" LINPHONE_DB;
	lInfo() << "Creating " LINPHONE_DB " at: " << path;
	d->mainDb.connect(MainDb::Sqlite3, path);
}

// -----------------------------------------------------------------------------

shared_ptr<ChatRoom> Core::createClientGroupChatRoom (const string &subject) {
	// TODO.
	return shared_ptr<ChatRoom>();
}

shared_ptr<ChatRoom> Core::getOrCreateChatRoom (const string &peerAddress, bool isRtt) const {
	return shared_ptr<ChatRoom>();
}

const list<shared_ptr<ChatRoom>> &Core::getChatRooms () const {
	L_D();
	return d->chatRooms;
}

string Core::getDataPath() const {
	L_D();
	return Paths::getPath(Paths::Data, static_cast<PlatformHelpers *>(d->cCore->platform_helper));
}

string Core::getConfigPath() const {
	L_D();
	return Paths::getPath(Paths::Config, static_cast<PlatformHelpers *>(d->cCore->platform_helper));
}

// -----------------------------------------------------------------------------

LINPHONE_END_NAMESPACE
