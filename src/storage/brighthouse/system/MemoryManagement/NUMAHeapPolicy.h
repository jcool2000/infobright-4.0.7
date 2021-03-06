/* Copyright (C)  2005-2008 Infobright Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2.0 as
published by the Free  Software Foundation.

This program is distributed in the hope that  it will be useful, but
WITHOUT ANY WARRANTY; without even  the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License version 2.0 for more details.

You should have received a  copy of the GNU General Public License
version 2.0  along with this  program; if not, write to the Free
Software Foundation,  Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA  */

#ifndef NUMAHEAPPOLICY_Y
#define NUMAHEAPPOLICY_Y

#include "HeapPolicy.h"
#include "TCMHeapPolicy.h"
#include "common.h"
#ifdef __GNUC__
#include <ext/hash_map>
#include "system/linux/hash_set_ext.h"
#ifndef stdext
#define stdext __gnu_cxx
#endif
#else
#include <hash_map>
#endif

#define MEM_HANDLE_BH void*


#ifdef USE_NUMA

class NUMAHeap : public HeapPolicy
{
public:
	NUMAHeap(size_t);
	virtual ~NUMAHeap();

	/*
		allocate memory block of size [size] and for data of type [type]
		type != BLOCK_FREE
	*/
	MEM_HANDLE_BH	alloc(	size_t size );
	void		dealloc(MEM_HANDLE_BH mh);
	MEM_HANDLE_BH	rc_realloc(MEM_HANDLE_BH mh, size_t size);

	size_t		getBlockSize(MEM_HANDLE_BH mh);
	
	private:
	
	typedef stdext::hash_map<int,TCMHeap *> NodeHeapType;
	typedef stdext::hash_map<MEM_HANDLE_BH,TCMHeap *> BlockHeapType;
	NodeHeapType m_nodeHeaps;
	BlockHeapType m_blockHeap;

	bool m_avail;
};

#else
typedef TCMHeap NUMAHeap;
#endif

#endif

