import socket

def ip_to_url(ip_address):
    try:
        url = socket.gethostbyaddr(ip_address)
        return url[0]
    except socket.herror:
        return "Unable to resolve IP to URL"

def url_to_ip(url):
    try:
        ip = socket.gethostbyname(url)
        return ip
    except socket.gaierror:
        return "Unable to resolve URL to IP"
	while True:
    print("1. IP to URL")
    print("2. URL to IP")
    choice = int(input("Enter your choice (1/2): "))

    if choice == 1:
        ip_address = input("Enter an IP address: ")
        url = ip_to_url(ip_address)
        print(f"URL for {ip_address}: {url}")
    elif choice == 2:
        url = input("Enter a URL: ")
        ip_address = url_to_ip(url)
        print(f"IP address for {url}: {ip_address}")
    else:
        print("Invalid choice. Please select 1 or 2.")
