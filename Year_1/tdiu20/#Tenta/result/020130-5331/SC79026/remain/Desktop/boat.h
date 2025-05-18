//boat.h


class Boat
{
public:
    Boat(int length);
    virtual ~Boat() = default;

    int get_length() const;
    virtual int calculate_security_factor() const;
    int calculate_load_capacity() const;
    virtual int calculate_reach() const = 0;
    
protected:
    int length{};
};

