#pragma once

#include "ParticleContact.h"

namespace phynet{
namespace phy{

template<int Dim>
class ParticleBaseLink
{
public:
	typedef Particle<Dim> ParticleType;
	typedef ParticleContact<Dim> ContactType;
	typedef typename math::Vector<Dim>::Type VectorType;

	ParticleBaseLink()
	{
		BaseInit(0.0f, 0);
	}
	
	Real GetMaxLenght()
	{
		return m_lenght;
	}

	virtual Real GetCurrentLenght() const
	{
		return m_lenght;
	}

	virtual const VectorType& GetEndPoint(UInt i_index) const = 0;
	virtual const ParticleType* GetParticle(UInt i_index) const = 0;
	virtual int AddContact(ContactType* o_contact) = 0;

protected:
	void BaseInit(const Real i_lenght, ParticleType* i_first)
	{
		m_firstParticle = i_first;
		m_lenght = i_lenght;
	}

	Real m_lenght;
	ParticleType* m_firstParticle;
};

template<int Dim>
class ParticleLink : public ParticleBaseLink<Dim>
{
public:
	ParticleLink()
	{
		LinkInit(0.0f, 0, 0);
	}
	
	virtual Real GetCurrentLenght()
	{
		return Distance(m_firstParticle->GetPosition(), m_secondParticle->GetPosition());
	}

	virtual const VectorType& GetEndPoint(UInt i_index) const
	{
		assert(i_index < 2);
		if(i_index == 0)
			return m_firstParticle->GetPosition();
		return m_secondParticle->GetPosition();
	}

	virtual const ParticleType* GetParticle(UInt i_index) const
	{
		assert(i_index < 2);
		if(i_index == 0)
			return m_firstParticle;
		return m_secondParticle;
	}

protected:
	void LinkInit(const Real i_lenght, ParticleType* i_first, ParticleType* i_second)
	{
		BaseInit(i_lenght, i_first);
		m_secondParticle = i_second;
	}

	ParticleType* m_secondParticle;
};

template<int Dim>
class ParticleAnchoredLink : public ParticleBaseLink<Dim>
{
public:
	ParticleAnchoredLink()
	{
		AnchoredLinkInit(0.0f, 0, VectorType::ZERO());
	}
	
	virtual Real GetCurrentLenght()
	{
		return Distance(m_firstParticle->GetPosition(), m_anchor);
	}

	virtual const VectorType& GetEndPoint(UInt i_index) const
	{
		assert(i_index < 2);
		if(i_index == 0)
			return m_firstParticle->GetPosition();
		return m_anchor;
	}

	virtual const ParticleType* GetParticle(UInt i_index) const
	{
		assert(i_index < 2);
		if(i_index == 0)
			return m_firstParticle;
		return 0;
	}

protected:
	void AnchoredLinkInit(const Real i_lenght, ParticleType* i_first, const VectorType& i_anchor)
	{
		BaseInit(i_lenght, i_first);
		m_anchor = i_anchor;
	}

	VectorType m_anchor;
};

}} // namespaces


