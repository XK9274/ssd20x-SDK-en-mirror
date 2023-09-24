# SSD20X screen click limit, determine whether the panel can be clicked
### illustrate
- Determining whether the panel is supported mainly depends on whether the clk of the panel is within the support range of SSD2X

### The spec of ssd20x clk is as follows:
- TTL output theory CLK supports range 9Mhz-75Mhz,
    - Calculation method: htotal * vtotal * fps
- MIPI DSI output theoretical CLK support range 100Mbps/lane – 1.5Gbps/lane
    - Calculation method: H_Total*V_Total*FPS*BitsPerPixel/lane number
    - BitsPerPixel=24(RGB888)/18(RGB666)/16(RGB565)


### other
- I have clicked on a 7Mhz TTL screen, so if the difference is not too big, there is still a chance that I can click on the screen normally.
