#include <Entity.hpp>
#include <Constants.hpp>

class SpikedTrap : public Entity {
public:
    SpikedTrap(int x, int y);
    virtual void draw() const;
    
private:
    char sprite = SPIKED_TRAP;
};