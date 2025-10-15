**Going to rewrite this to sound more like a project report rather than a guide**

# Overview

This project is a lightweight, portable, cheap, and effective response to malicious drones. Below you'll find a more in depth look at the requirements for this project, as well as other information necessary for operation and installation (subject to change. just coming up with stuff)

# Features

The Drone C-RAM features rotating up to 25rpm, drone detection with the Raspberry Pi AI camera, tracking / target leading capabilites, and precise motor control with a software proportional-integral-derivative (PID) controller.

The target-leading mechanism is based off of the target's position and speed. The basic idea is best illustrated with pseudo-code: 

```c
  int x = 250;
  int y = 300;
  int dx = 0;
  int dy = 0;

while(i) {
  target(x, y); // A target at x, y
  x = x + dx;
  y = y + dy;
  if(x > 200){ // causes the movement of the target
    dx--;
  }else if(x < 200){
    dx++;
  }
  if(y > 200){
    dy--;
  }else if(y < 200){
    dy++;
  }
  // This crosshair leads the target by an arbitrary "10" units.
  // This var would change if you wanted to lead the target by more or less.
  // The crosshair currently does not take into account the movement curve
  // of the target.
  crosshair(x+10*dx, y+10*dy, x+10*dx, y+10*dy);
}
```

![target-leading](Media/proposed-tracking-method.gif)

# Hardware Requirements

* 3D printer. Ideally with >13" print height.
* 3D printer filament
* Materials to program your Raspberry Pi with (monitor, keyboard, etc.)
* (5) 5mm x 250mm 304 Stainless Steel Solid Round Rod [(+)](https://www.amazon.com/dp/B082ZNJR7D?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
* (12) Set Screw Collars [(+)](https://www.amazon.com/dp/B0F9P5CNSL?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
* (15) Ball Bearings 5mm Bore 16mm OD [(+)](https://www.amazon.com/dp/B0CJFSBRTJ?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
* (4) Flange Coupling Connector [(+)](https://www.amazon.com/dp/B0DN6P9B36?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
* (2) Timing Pulley Set [(+)](https://www.amazon.com/dp/B09TKZS2QB?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
* Turntable Bearing [(+)](https://www.amazon.com/dp/B08CSMYXFV?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
* Raspberry Pi AI camera [(+)](https://www.adafruit.com/product/6009?srsltid=AfmBOoqx1-qlwzmA9ndyD2iXr5zASwpQUE9RnnWQQf-xEFGbjSt2rt4W)
* Stepper motor cables [(+)](https://www.amazon.com/dp/B07PZWXBFB?ref=cm_sw_r_cp_ud_dp_1X9T1BPMR68DE28PW7KQ&ref_=cm_sw_r_cp_ud_dp_1X9T1BPMR68DE28PW7KQ&social_share=cm_sw_r_cp_ud_dp_1X9T1BPMR68DE28PW7KQ&th=1)
* Power supply [(+)](https://www.amazon.com/dp/B0CGHSTDYM?ref_=cm_sw_r_cp_ud_ct_X4HZC6Q636RNBEGBQEZB_1&th=1)
* Jumper cables [(+)](https://www.amazon.com/dp/B0CGHSTDYM?ref_=cm_sw_r_cp_ud_ct_X4HZC6Q636RNBEGBQEZB_1&th=1)
* Raspberry Pi 5 8GB [(+)](https://www.amazon.com/dp/B0CK2FCG1K?ref=cm_sw_r_cp_ud_dp_GCMPT41GAGKDGNSQ515B&ref_=cm_sw_r_cp_ud_dp_GCMPT41GAGKDGNSQ515B&social_share=cm_sw_r_cp_ud_dp_GCMPT41GAGKDGNSQ515B)
* (2) TB6600 stepper motor drivers [(+)](https://www.amazon.com/dp/B0BZYX7Z4Z?ref=cm_sw_r_cp_ud_dp_VXDE926C0Y0TAD7345C3&ref_=cm_sw_r_cp_ud_dp_VXDE926C0Y0TAD7345C3&social_share=cm_sw_r_cp_ud_dp_VXDE926C0Y0TAD7345C3&th=1)
* Full automatic arisoft gun (some prints made specific to our model [(+)](https://www.amazon.com/dp/B07XJ9K5KT?ref=cm_sw_r_cp_ud_dp_9KHN7P3S4Y6VA8SVB0YQ&ref_=cm_sw_r_cp_ud_dp_9KHN7P3S4Y6VA8SVB0YQ&social_share=cm_sw_r_cp_ud_dp_9KHN7P3S4Y6VA8SVB0YQ&th=1))
* Slip joint [(+)](https://www.amazon.com/dp/B07XJ9K5KT?ref=cm_sw_r_cp_ud_dp_9KHN7P3S4Y6VA8SVB0YQ&ref_=cm_sw_r_cp_ud_dp_9KHN7P3S4Y6VA8SVB0YQ&social_share=cm_sw_r_cp_ud_dp_9KHN7P3S4Y6VA8SVB0YQ&th=1)

# Software Requirements

* 

# Installation

## Wiring Diagram


## CAD Files

We used a total of seven 3D printed parts on this project. You can find them [here.](CAD-files)


# Acknowledgements
