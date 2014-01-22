#ifndef _CMDOPTION_STRING_H_
#define _CMDOPTION_STRING_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/**
 * ����ָ���ַ�����
 */

#include <string>
#include <algorithm>

namespace copt
{
    /**
     * �������޵��ַ������ʹ�����
     */
    template<typename Tc>
    struct ci_char_traits: public std::char_traits<Tc>
    {
        static bool eq(Tc left, Tc right) { return toupper(left) == toupper(right);  }
        static bool lt(Tc left, Tc right) { return toupper(left) < toupper(right);  }

        static int compare(const Tc* left, const Tc* right, size_t n) { 
            while(n -- > 0)
            {
                char cl = toupper(*left), cr = toupper(*right);
                if(cl < cr)
                    return -1;
                else if(cl > cr)
                    return 1;

                ++ left, ++ right;
            }
            return 0; 
        }

        static const Tc* find(const char* s, int n, Tc a)
        {
            while( n -- > 0 && toupper(*s) != toupper(a) )
                ++ s;
            return n >= 0 ? s: 0;
        }
    };

    // �����ض���
    typedef std::basic_string<char, ci_char_traits<char> > CmdOptionCIString;
}

#endif
