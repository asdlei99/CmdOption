/**
* @file std_check.h
* @brief ���C++0x/11��������
* Licensed under the MIT licenses.
*
* @version 1.0
* @author OWenT, owt5008137@live.com
* @date 2014.01.21
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
// ���C++0x/11��������
// ============================================================

// VC12.0 SP1���Ϸ�֧�ж�
#if defined(__cplusplus) && __cplusplus >= 201103L
    #define COPT_ENABLE_VARIADIC_TEMPLATE 1
#elif defined(_MSC_VER) && (_MSC_VER >= 1800 && defined(_HAS_CPP0X) && _HAS_CPP0X)
    #define COPT_ENABLE_VARIADIC_TEMPLATE 1
#elif defined(__clang__) && __clang_major__ >= 3 && (__cplusplus >= 201103L || !defined(_LIBCPP_HAS_NO_VARIADICS))
    #define COPT_ENABLE_VARIADIC_TEMPLATE 1
#elif defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 4
// ����G++ std::tr1��
    #if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
        #define COPT_ENABLE_VARIADIC_TEMPLATE 1
    #endif
#endif
#endif
