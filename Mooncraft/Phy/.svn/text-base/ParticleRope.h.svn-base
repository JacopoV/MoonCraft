#pragma once

#include "ParticleLink.h"

namespace phynet{
namespace phy{

template<int Dim>
class ParticleRope : public ParticleLink<Dim>
{
public:
	ParticleRope();
	void Init(const Real i_lenght, ParticleType* i_first, ParticleType* i_second, const Real i_restitution);

	virtual int AddContact(ContactType* o_contact);

private:
	Real m_restitution;
};

template<int Dim>
class ParticleAnchoredRope : public ParticleAnchoredLink<Dim>
{
public:
	ParticleAnchoredRope();
	void Init(const Real i_lenght, ParticleType* i_first, const VectorType& i_anchor, const Real i_restitution);

	virtual int AddContact(ContactType* o_contact);

private:
	Real m_restitution;
};

}} // namespaces

#include "ParticleRope.inl"

