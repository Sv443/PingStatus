## Roadmap
- Support photoresistor as a trigger for auto-dimming
    - calculate the PWM value from the photoresistor so it changes brightness dynamically
- Add support for pinging domains by looking up the IP via DoH [see this](https://developers.cloudflare.com/1.1.1.1/encryption/dns-over-https/make-api-requests/)
    - example: `curl -H 'accept: application/dns-json' 'https://cloudflare-dns.com/dns-query?name=example.com&type=A'`
- Add a comprehensible way to configure config settings like active low and on/off time per client

<br>

## v0.2.0 (WIP)
- Auto-dimming LEDs based on ambient light by reading an LDR
- Added DoH support to send a GET/HEAD <!--(TODO)--> request to certain domains
- Made configuring clients a bit easier
- Added momentary button to temporarily disable auto-shutoff mode

<br>

## v0.1.0
- Added basic pinging of any amount of clients
- Added auto-dimmer function
