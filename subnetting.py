import math

def calculate_subnet_mask(N, check_class):
    mask_bits = math.ceil(math.log(N) / math.log(2))
    
    if check_class <= 127:
        mask = "255.0.0.0"
        mask_b = 8 + mask_bits
        return mask, mask_b, "Class A IP Address"
    elif 128 <= check_class <= 191:
        mask = "255.255.0.0"
        mask_b = 16 + mask_bits
        return mask, mask_b, "Class B IP Address"
    elif 192 <= check_class <= 223:
        mask = "255.255.255.0"
        mask_b = 24 + mask_bits
        return mask, mask_b, "Class C IP Address"
    elif 224 <= check_class <= 239:
        mask = "255.0.0.0"
        return mask, None, "Class D IP Address Used For Multicasting"
    elif 240 <= check_class <= 254:
        mask = "255.0.0.0"
        return mask, None, "Class E IP Address Experimental Use"
    
    def calculate_network_and_last_addr(ip, mask):
        network_addr = ""
        last_addr = ""
        ip_addr_parts = [int(part) for part in ip.split(".")]
        mask_parts = [int(part) for part in mask.split(".")]
    
        for i in range(4):
            z = ip_addr_parts[i] & mask_parts[i]
            network_addr += str(z) + "."
            w = z | (mask_parts[i] ^ 255)
            last_addr += str(w) + "."
    
        return network_addr[:-1], last_addr[:-1]

    ip = input("Enter IP: ")
    check_class = int(ip.split(".")[0])
    N = int(input("Enter the number of subnets: "))

    mask, mask_b, class_info = calculate_subnet_mask(N, check_class)
    print(f"{class_info}")
    print(f"Subnet Mask: {mask}")
    print(f"No. of 1's in the subnet mask: {mask_b}")

    network_addr, last_addr = calculate_network_and_last_addr(ip, mask)
    print(f"First IP of block: {network_addr}")
    print(f"Last IP of block: {last_addr}")
    