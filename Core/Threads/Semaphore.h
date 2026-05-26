#ifndef SEMAPHORE_H__INCLUDED
#define SEMAPHORE_H__INCLUDED

#include "../PrimitivesTypes.h"
#include <semaphore>

namespace TNgine
{
    class Semaphore
    {
    public:

        Semaphore(uint32 initialCount = 0);

        void Release(uint32 count = 1);

        void Acquire();

    private:

        std::counting_semaphore<> m_Semaphore;
    };
}

#endif // !SEMAPHORE_H__INCLUDED