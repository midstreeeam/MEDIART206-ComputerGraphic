// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

// A class for a draggable attractive body in our world

class catcher {
public:
    
    float mass;    // Mass, tied to size
    float G;       // Gravitational Constant
    ofPoint location;   // Location
    bool dragging = false; // Is the object being dragged?
    bool rollover = false; // Is the mouse over the ellipse?
    ofPoint dragOffset;  // holds the offset for when object is clicked on
    
    catcher() {
        location.set(ofGetWidth()/1.5,ofGetHeight()/2);
        mass = 20;
        G = 20;
        dragOffset.set(0,0);
    }
    
    ofPoint attract(mover m) {
        ofPoint force;
        force.set(location);
        force -= m.location;                                // Calculate direction of force
        float d = force.length();                           // Distance between objects
        d = ofClamp(d, 50.0, 90.0);                          // Limiting the distance to eliminate "extreme" results for very close or very far objects
        force.normalize();                                  // Normalize vector (distance doesn't matter here, we just want this vector for direction)
		float strength = (G * mass * m.mass) / (d * d);     // Calculate gravitional force magnitude
        force *= strength;                                  // Get force vector --> magnitude * direction
        return force;
    }
    
    // Method to display
    void display() {
		ofSetColor(100, 20);
		ofDrawCircle(location, 100);
        if (dragging) ofSetColor(50);
        else if (rollover) ofSetColor(80);
        else ofSetColor(100,200);
        ofDrawCircle(location.x,location.y,mass);
    }
    
    // The methods below are for mouse interaction
    void clicked(int mx, int my) {
        ofPoint a;
        ofPoint b;
        a.set(mx,my);
        b.set(location.x,location.y);
        b -= a;
        float d = b.length();
        if (d < mass) {
            dragging = true;
            dragOffset.x = location.x-mx;
            dragOffset.y = location.y-my;
        }
    }
    
    void hover(int mx, int my) {
        ofPoint a;
        ofPoint b;
        a.set(mx,my);
        b.set(location.x,location.y);
        b -= a;
        float d = b.length();
        if (d < mass) {
            rollover = true;
        }
        else {
            rollover = false;
        }
    }
    
    void stopDragging() {
        dragging = false;
    }
    
    
    
    void drag() {
        if (dragging) {
            location.x = ofGetMouseX() + dragOffset.x;
            location.y = ofGetMouseY() + dragOffset.y;
        }
    }
    
};