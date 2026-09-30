# disaster_ai.py

from scapy.all import Ether, Raw, sendp


# =========================================================
# Ethernet Configuration
# =========================================================

BOARD_MAC = "00:11:22:33:44:55"

PC_MAC = "00:0E:09:86:93:93"

# IMPORTANT:
# Keep the NPF interface that is currently working on your PC.
INTERFACE = r"\Device\NPF_{A5E823A8-3D1F-4F99-9910-69C0BC87E475}"


# =========================================================
# Disaster Classification
# =========================================================

def classify_disaster(text):

    text = text.lower()

    # FIRE
    if any(word in text for word in [
        "fire",
        "flames",
        "burning",
        "smoke",
        "building on fire"
    ]):
        return "FIRE"

    # MEDICAL
    elif any(word in text for word in [
        "injured",
        "injury",
        "injured hand",
        "hand is injured",
        "ambulance",
        "medical",
        "hospital",
        "people trapped"
    ]):
        return "MEDICAL"

    # ROAD
    elif any(word in text for word in [
        "road blocked",
        "roadblock",
        "traffic blocked",
        "landslide",
        "bridge blocked",
        "road damage"
    ]):
        return "ROAD"

    # NORMAL
    else:
        return "NORMAL"


# =========================================================
# Send Disaster Information to RA8P1
# =========================================================

def send_to_ra8p1(category, message):

    # Send both category and original message
    # Format:
    # CATEGORY|ORIGINAL MESSAGE

    payload_text = f"{category}|{message}"

    payload = payload_text.encode("ascii", errors="ignore")

    # Ethernet minimum payload = 46 bytes
    if len(payload) < 46:
        payload = payload + b"\x00" * (46 - len(payload))

    packet = (
        Ether(
            dst=BOARD_MAC,
            src=PC_MAC,
            type=0x0800
        )
        /
        Raw(payload)
    )

    print("\nSending to RA8P1...")
    print("Category :", category)
    print("Message  :", message)

    sendp(
        packet,
        iface=INTERFACE,
        verbose=True
    )

    print("Packet sent successfully.")


# =========================================================
# Main Program
# =========================================================

print("========================================")
print("   AI Disaster Communication System")
print("========================================")

message = input("\nEnter disaster information: ")

category = classify_disaster(message)

print("\nDisaster Information :", message)
print("Detected Category    :", category)

send_to_ra8p1(category, message)