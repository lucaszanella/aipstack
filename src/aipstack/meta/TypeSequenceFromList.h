/*
 * Copyright (c) 2014 Ambroz Bizjak
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

#ifndef AIPSTACK_TYPE_SEQUENCE_FROM_LIST_H
#define AIPSTACK_TYPE_SEQUENCE_FROM_LIST_H

#include <aipstack/meta/TypeSequence.h>
#include <aipstack/meta/TypeListUtils.h>

namespace AIpStack {

/**
 * @addtogroup meta
 * @{
 */

#ifndef IN_DOXYGEN

template<typename, typename>
struct TypeSequenceFromListHelper;

template<typename List, typename ...Indices>
struct TypeSequenceFromListHelper<List, TypeSequence<Indices...>> {
#ifdef _MSC_VER
    template<int Index>
    struct Hack {
        using Elem = TypeListGet<List, Index>;
    };
    
    using Result = TypeSequence<typename Hack<Indices::Value>::Elem...>;
#else
    using Result = TypeSequence<TypeListGet<List, Indices::Value>...>;
#endif
};

#endif

template<typename List>
using TypeSequenceFromList =
    #ifdef IN_DOXYGEN
    implementation_hidden;
    #else
    typename TypeSequenceFromListHelper<List, TypeSequenceMakeInt<TypeListLength<List>>>::Result;
    #endif

/** @} */

}

#endif
