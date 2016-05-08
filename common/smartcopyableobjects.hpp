
/*
  Devoir1
  Julien De Loor (julien.de-loor1@uqac.ca) 
  Classe pour copier simplement des gros objets en faisant des copies réeles uniquement 
  lorsque l'on veux modifier l'objet. 
*/

#pragma once

#include <memory> // C++ 11
#include <cassert>
#include <iostream>

template<class C> //C need a copy constructor
class SmartCopyableObject
{

protected:
  std::shared_ptr<C> _object;       //Our heavy memory object

private:
  const SmartCopyableObject*              _base;  //Object we have copied
  mutable SmartCopyableObject*       _derivated;  //Object that copied us

public:
  SmartCopyableObject(C* object):
    _object(object),
    _base(nullptr),
    _derivated(nullptr)
  {
  
  }

  SmartCopyableObject(const SmartCopyableObject<C>& o):
    _object(o._object),
    _base(nullptr),
    _derivated(nullptr)
  {
    _base = o.getBasePtr(this);
  }

  virtual ~SmartCopyableObject()
  {
    destroy();
  }

  
  void smartcopy(const SmartCopyableObject<C>& o)
  {
    destroy();
    _object = o._object;
    _base = o.getBasePtr(this);
  }

  //Call this when you affect your object with a non const fonction
  inline void ensureUnique()
  {
    hardcopy();
  }

  //Remove parent/child link by hardcopy the object
  //Call this when the object need to be modified
  void hardcopy()
  {
    if (_object.unique() || !_object || (_base == nullptr && _derivated == nullptr))
    {
      return; //No need to copy 
    }
    
    std::cout << "(" << this << ")" << " hardcopy of data " << _object.get() << std::endl;

    std::shared_ptr<C> copy(new C(*_object)); //Hard copy (C need a copy constructor)
    destroy();
    _object = copy;
  }

protected:

  const SmartCopyableObject<C>* getBasePtr(SmartCopyableObject<C>* derivated) const
  {
    if (_derivated == nullptr)
    {
      _derivated = derivated;
      return this;
    }
    else
    {
      return _derivated->getBasePtr(derivated);
    }
  }

private:

  inline void destroy()
  {
    _object.reset((C*)nullptr);
    if (_base != nullptr)
    {
      _base->_derivated = _derivated;
      if (_derivated != nullptr)
      {
        _derivated->_base = _base;
      }
    }
    else if (_derivated != nullptr)
    {
      //Derivated take ownership
      _derivated->_base = nullptr;
    }
    _base = nullptr;
    _derivated = nullptr;
  }


};