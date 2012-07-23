#pragma once

#include "ParticleLink.h"

namespace phynet{
namespace phy{

template<int Dim>
class ParticleRod : public ParticleLink<Dim>
{
public:
	ParticleRod();
	void Init(const Real i_lenght, ParticleType* i_first, ParticleType* i_second);
	void Init(ParticleType* i_first, ParticleType* i_second); //self deduce lenght

	virtual int AddContact(ContactType* o_contact);
};

template<int Dim>
class ParticleAnchoredRod : public ParticleAnchoredLink<Dim>
{
public:
	ParticleAnchoredRod();
	void Init(const Real i_lenght, ParticleType* i_first, const VectorType& i_anchor); 
	void Init(ParticleType* i_first, const VectorType& i_anchor); //self deduce lenght

	virtual int AddContact(ContactType* o_contact);
};

}} // namespaces

#include "ParticleRod.inl"

