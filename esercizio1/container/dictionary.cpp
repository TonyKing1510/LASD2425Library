
namespace lasd {

/* ************************************************************************** */

template <typename Data>
    inline bool lasd::DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &con)
    {
        bool all = true;
        con.Traverse(
            [this, &all](const Data &dat)
            {
                all &= this->Insert(dat);
            });
        return all;
    }
    template <typename Data>
    inline bool lasd::DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&map)
    {
        bool all = true;
        map.Map(
            [this, &all](const Data &dat)
            {
                all &= this->Insert(std::move(dat));
            });
        return all;
    }
    template <typename Data>
    inline bool lasd::DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& con)
    {
        bool all = true;
        con.Traverse(
            [this, &all](const Data &dat)
            {
                all &= this->Remove(dat);
            });
        return all;
    }
    template <typename Data>
    inline bool lasd::DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &con)
    {
        bool some = false;
        con.Traverse(
            [this, &some](const Data &dat)
            {
                some |= Insert(dat);
            });
        return some;
    }
    template <typename Data>
    inline bool lasd::DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&map)
    {
        bool some = false;
        map.Map(
            [this, &some](Data &dat)
            {
                some |= this->Insert(std::move(dat));
            });
        return some;
    }
    template <typename Data>
    inline bool lasd::DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &con)
    {
        bool some = false;
        con.Traverse(
            [this, &some](const Data &dat)
            {
                some |= this->Remove(dat);
            });
        return some;
    }

/* ************************************************************************** */

}
