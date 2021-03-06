/*
 * Copyright (C) 2003-2014 The Music Player Daemon Project
 * http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPD_ID_TABLE_HXX
#define MPD_ID_TABLE_HXX

#include "Compiler.h"

#include <algorithm>

#include <assert.h>

/**
 * A table that maps id numbers to position numbers.
 */
class IdTable {
	unsigned size;

	unsigned next;

	int *data;

public:
	IdTable(unsigned _size):size(_size), next(1), data(new int[size]) {
		std::fill_n(data, size, -1);
	}

	~IdTable() {
		delete[] data;
	}

	int IdToPosition(unsigned id) const {
		return id < size
			? data[id]
			: -1;
	}

	unsigned GenerateId() {
		assert(next > 0);
		assert(next < size);

		while (true) {
			unsigned id = next;

			++next;
			if (next == size)
				next = 1;

			if (data[id] < 0)
				return id;
		}
	}

	unsigned Insert(unsigned position) {
		unsigned id = GenerateId();
		data[id] = position;
		return id;
	}

	void Move(unsigned id, unsigned position) {
		assert(id < size);
		assert(data[id] >= 0);

		data[id] = position;
	}

	void Erase(unsigned id) {
		assert(id < size);
		assert(data[id] >= 0);

		data[id] = -1;
	}
};

#endif
