#pragma once
#include "ecm.h"

class PickupComponent : public Component {
protected:
	float points;

public:
	PickupComponent() = delete;
	explicit PickupComponent(Entity* parent, bool big);

	void update(double dt) override;
	void render() override;
};