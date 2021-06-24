#ifndef Actuator_H
#define Actuator_H

#define clamp(x,a,b) (x<a?a:(x>b?b:x))

class Actuator{
  protected:
    // Wrapper functions
    virtual void update() = 0;
    virtual bool init() = 0;
    //Has begin() been performed by THIS object?
    bool ready = false;
  public:
    /**
     * Hardware ID.
    */
    String id;
    /**
     * Meaningful, readable name of the actuator.
    */
    String name;
    /**
     * Preformatted (lowercase and underscored) name of the environment variable the actuator controls.
    */
    String evname;
    float target;
    Actuator(String name, String id, String evname);
    void updateActuator();
    bool begin();
};

#endif 