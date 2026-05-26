#ifndef TASK_H__INCLUDED
#define TASK_H__INCLUDED

namespace TNgine
{
    class Task
    {
    public:

        virtual ~Task() = default;

        virtual void Execute() = 0;
    };
}


#endif //!TASK_H__INCLUDED