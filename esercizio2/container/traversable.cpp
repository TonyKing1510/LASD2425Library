
namespace lasd {

/* ************************************************************************** */

//funzioni di PreOrder
template<typename Data>
template<typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun ,Accumulator acc) const{
     return dynamic_cast<const PreOrderTraversableContainer<Data>*>(this)->PreOrderFold(fun, acc);
};

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data& key)const noexcept
{
    bool exists=false;
    Traverse(
        [key, &exists](const Data &dat)
        {
            if(dat == key)
            {
                exists=true;
            }
        });
    return exists;
}

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const
{
    PreOrderTraverse(
        [fun,&acc](const Data &dat)
        {
            acc=fun(dat,acc);
        }
    );
    return acc;
}
template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const
{
    PreOrderTraverse(fun);
}
/* ************************************************************************** */

//funzioni di postOrder

template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const
{
    PostOrderTraverse(
        [fun, &acc](const Data &dat)
        {
            acc = fun(dat, acc);
        });
    return acc;
}

template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const
{
    PostOrderTraverse(fun);
}



/* ************************************************************************** */

}
