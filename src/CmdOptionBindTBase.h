#ifndef _CMDOPTIONBINDTBASE_H_
#define _CMDOPTIONBINDTBASE_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/*
 * CmdOptionBindTBase.h
 *
 *  Created on: 2012-01-18
 *      Author: OWenT
 *
 * �������༰��������
 */

#include "CmdOptionList.h"

namespace copt
{
    // ��׼ָ�������������
    
    // ��׼ָ�����(�޷���ֵ������Ϊѡ���ӳ���)
    // void function_name (CmdOptionList&, [����]); // ����������ѡ
    // void function_name (callback_param, [����]); // ����������ѡ

    // ��������
    namespace binder {
        // �����������ṹ����
        template<class _R, class _F, class _PL> 
        class CmdOptionBindT : public CmdOptionBindBase
        {
        protected:
            _F m_fFuncObj;      // �����ṹ
            _PL m_stParamList;   // �����б�ṹ

        public:
            typedef CmdOptionBindT this_type;

            CmdOptionBindT(_F f, _PL l): m_fFuncObj(f), m_stParamList(l) {}

            void operator()(callback_param args)
            {
                m_stParamList(m_fFuncObj, args, 0);
            }                      
        };

    }
}
#endif /* _CMDOPTIONBIND_H_ */
