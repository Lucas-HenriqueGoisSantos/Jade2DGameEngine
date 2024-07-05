#ifndef ECS_H
#define ECS_H

class Component {

};

class Entity {

private:
	int id;

public:
	Entity( int id ) : id( id ) {};
	int GetId() const;

};

class system {

};

class Registry {

};

#endif // !ECS_H
