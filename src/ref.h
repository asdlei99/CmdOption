/**
* @file functional.h
* @brief �������ð�װ
* Licensed under the MIT licenses.
*
* @version 1.0
* @author OWenT, owt5008137@live.com
* @date 2012.08.02
*
* @history
*
*/

#ifndef _STD_REF_H_
#define _STD_REF_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// ============================================================
// ������������
// �Զ��������ð�װ��
// ============================================================

/**
* �������ð�װ��std::ref, std::cref, std::reference_wrapper��
* �����G++��֧��c++0x�ݰ�1��tr1�汾����smart_ptr[GCC�汾����4.0]
* �������GNU-C++�����ð�װ
*
* �����VC++��֧��c++0x�ݰ�1��tr1�汾����smart_ptr[VC++�汾����9.0 SP1]
* �������VC++�����ð�װ
*
* ��������boost�е����ð�װ�⣨��������������Ҫ����boost�⣩
*/

// VC9.0 SP1���Ϸ�֧�ж�
#if defined(_MSC_VER) && (_MSC_VER == 1500 && defined (_HAS_TR1)) || (_MSC_VER > 1500 && defined(_HAS_CPP0X) && _HAS_CPP0X)
// ����VC std::tr1��
#include <functional>
#elif defined(__clang__) && __clang_major__ >= 3
// ����Clang c++11��
#include <functional>
#elif defined(__GNUC__) && __GNUC__ >= 4
// ����G++ std::tr1��
#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
#include <functional>
#else
#include <tr1/functional>
namespace std {
    using tr1::ref;
    using tr1::cref;
    using tr1::reference_wrapper;
}
#endif
#else
// ����boost tr1��
#include <boost/tr1/functional.hpp>
namespace std {
    using tr1::ref;
    using tr1::cref;
    using tr1::reference_wrapper;
}
#endif

#endif
