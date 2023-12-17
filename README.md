# R3X-Servos

Project use 2 Arduino Nano connects via pins 4 - 4 and pins 5 - 5 for SDA the second arduino controls a dfplayer for mp3's and has envelope follower to read the dac output from the dfplayer and control the mouth lights.
This arduino is also connected via serial on pins 10 & 11 to a Pololu Maestro to control all the servos. I've let the pololu handle all the max servo movements so the code can't exceed them. I'm also using the pololu to handle the speed/acceleration functions to smooth the movement.
