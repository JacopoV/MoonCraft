#pragma once

namespace phynet
{

template<typename Container>
inline void erase_unordered(Container& v, typename Container::iterator it)
{
    typename Container::const_iterator lastElementIt = v.end() - 1;
	*it = *lastElementIt;
    v.pop_back();
}

template<typename Container>
inline void erase_unordered(Container& v, typename const Container::value_type& value)
{
	typename Container::iterator it = std::find(v.begin(), v.end(), value);
	if(it != v.end())
		erase_unordered(v, it);
}

template<typename Container>
inline typename Container::iterator erase_unordered_ret(Container& v, typename Container::iterator it)
{
	//assert(!v.empty());
	if (it+1 != v.end())
	{
		*it = v.back();
		v.pop_back();
		return it;
	}
	v.pop_back();
	return v.end();
}

template <typename Container>
inline void RemoveAll_unordered(Container& o_container, const typename Container::value_type& i_value)
{
	typename Container::iterator it = std::find(o_container.begin(), o_container.end(), i_value);
	while(it != o_container.end())
	{
		it = erase_unordered_ret(o_container, it);
		it = std::find(it, o_container.end(), i_value);
	}
}

template <typename Container, typename Pred>
inline void RemoveAll_unordered(Container& o_container, Pred i_pred)
{
	typename Container::iterator it = std::find_if(o_container.begin(), o_container.end(), i_pred);
	while(it != o_container.end())
	{
		it = erase_unordered_ret(o_container, it);
		it = std::find_if(it, o_container.end(), i_pred);
	}
}

template<typename Container>
inline void RemoveAll(Container& o_container, const typename Container::value_type& i_value)
{
	o_container.erase(std::remove(o_container.begin(), o_container.end(), i_value), o_container.end());
}

template<typename Container>
inline void DeepClear(Container& o_container)
{
	typedef typename Container::iterator Iter;
	for(Iter i = o_container.begin(); i != o_container.end(); ++i)
		delete *i;
	o_container.clear();
}

template<typename DestContainer, typename SourceContainer>
inline void Append(DestContainer& o_dest, const SourceContainer& i_src)
{
	o_dest.reserve(o_dest.size() + i_src.size());
	std::copy(i_src.begin(), i_src.end(), std::back_inserter(o_dest));
}

template<typename Container>
inline void InsertUnique(const typename Container::value_type& i_elem, Container& o_container)
{
	typename Container::const_iterator i = std::find(o_container.begin(), o_container.end(), i_elem);
	if (i == o_container.end())
		o_container.push_back(i_elem);
}

} // namespace phynet

