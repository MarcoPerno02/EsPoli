import struct

# List of hexadecimal values from the image
hex_values = [
    "c042800000000000", "405b800000000000", "4057800000000000", "404d800000000000", 
    "403f000000000000", "4053400000000000", "404d000000000000", "4035000000000000", 
    "404f000000000000", "3ff0000000000000", "4046000000000000"
]

# Function to convert hex to double precision floating-point
def hex_to_double(hex_value):
    return struct.unpack('>d', bytes.fromhex(hex_value))[0]

# Convert all hex values
decimal_values = [hex_to_double(hv) for hv in hex_values]
print(decimal_values)
