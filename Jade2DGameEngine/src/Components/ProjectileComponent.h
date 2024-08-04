#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H


struct ProjectileComponent {

	bool isFriendly;
	int hitPercentDamage;
	int duration;
	int startTime;

	ProjectileComponent( bool isFriendly, int hitPercentDamage, int duration, int startTime ) {

	}
};


#endif // !PROJECTILECOMPONENT_H