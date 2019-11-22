# gage-particle [![Codacy Badge](https://api.codacy.com/project/badge/Grade/d3b17f125ebe462da8480e43eff847c1)](https://www.codacy.com?utm_source=github.com&utm_medium=referral&utm_content=abkfenris/gage-particle&utm_campaign=Badge_Grade)

Building a river gage using Particle.io with to incorperate what I learned during my last attempt.

## Particle.io Functions

Various settings controlling the device can be set via the Particle.io console (or via API).

- `settings-ubidots_update_seconds` - Set the number of seconds between sending updates to Ubidots. Defaults to 30 during testing. Should be increased once deployed. Sending `'stop'` should stop updates all together.
- `wifi_add_network` - You can add a new network to the device remotely (when it's already connected to a network it knows). Call the function with `ssid:password` to add the new SSID. Or use `particle serial wifi`.

## Learnings

Some of the things that I learned last time.

- Power is hard, reliability of single board computers in the Maine elements is harder.
- Use a third party data system until the device is reliable. No need for dealing with having your own server down while trying to debug the device.
- Paying for a system with integrated networking and power is worth it.
- Don't try to develop the server and the device at the same time from scratch.
