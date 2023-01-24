## Roadmap
- Support photoresistor as a trigger for auto-dimming
    - the PWM value from the photoresistor so it changes brightness dynamically
- Add support for pinging domains by looking up the IP via DoH [see this](https://developers.cloudflare.com/1.1.1.1/encryption/dns-over-https/make-api-requests/)
    - example: `curl -H 'accept: application/dns-json' 'https://cloudflare-dns.com/dns-query?name=example.com&type=A'`

<br>

## v0.1.0
- Added basic pinging of any amount of clients
- Added auto-dimmer function
