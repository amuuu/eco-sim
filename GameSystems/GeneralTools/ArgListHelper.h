#pragma once

namespace ArgListHelper
{

    struct Args
    {
        void* item;
        Args* next{ nullptr };
    };

    template <typename Arg, typename... ArgRest>
    static void PackArgs(Args* args, Arg arg, ArgRest...rest)
    {
        args->item = new Arg{ arg };

        if constexpr (sizeof...(rest) > 0)
        {
            args->next = new Args{};
            PackArgs(args->next, rest...);
        }
    }

    template<typename Arg>
    static Arg ExtractFromArgs(Args* p)
    {
        return *(static_cast<Arg*>(p->item));
    }


    // todo: fix this vvvvvvvvvvvvvvvv
    /*
    template<typename Arg>
    static Arg ExtractFromArgsUnordered(Args* p)
    {
        Args* current = p;

        while (current != nullptr)
        {
            if (auto* target = dynamic_cast<Arg*>(current->item); target != nullptr)
            {
                return target;
            }
            else
            {
                current = current->next;
            }
        }

        return nullptr;
    }
    */
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Visual studio MSVC compiler has a bug which causes the following class to not compile. I submitted an issue here:
// https://developercommunity.visualstudio.com/t/VS2022-1744-C17-C1004-unexpected/10265019
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

template <typename Arg, typename... ArgRest>
class PayloadPacker
{
public:

    Args* payload{ nullptr };

    PayloadPacker(const Arg& arg, const ArgRest&...rest) : payload{ new Args{} }
    {
        ::PackArgs(payload, arg, rest...);
    }

    ~PayloadPacker()
    {
        delete payload;
    }
};

*/