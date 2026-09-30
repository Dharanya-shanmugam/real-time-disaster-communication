from flask import Flask, request
from scapy.all import Ether, Raw, sendp

app = Flask(__name__)


# ========================================
# ETHERNET CONFIGURATION
# ========================================

BOARD_MAC = "00:11:22:33:44:55"
PC_MAC = "00:0E:09:86:93:93"

INTERFACE = r"\Device\NPF_{A5E823A8-3D1F-4F99-9910-69C0BC87E475}"


# ========================================
# AI DISASTER CLASSIFICATION
# ========================================

def classify_disaster(text):

    text = text.lower()

    if any(word in text for word in [
        "fire",
        "flames",
        "burning",
        "smoke",
        "building on fire"
    ]):
        return "FIRE"

    elif any(word in text for word in [
        "sick",
        "ill",
        "illness",
        "not feeling well",
        "fever",
        "injured",
        "injury",
        "ambulance",
        "medical",
        "hospital",
        "people trapped"
    ]):
        return "MEDICAL"

    elif any(word in text for word in [
        "road blocked",
        "roadblock",
        "traffic blocked",
        "landslide",
        "bridge blocked",
        "road damage"
    ]):
        return "ROAD"

    else:
        return "NORMAL"


# ========================================
# SEND CATEGORY TO RA8P1
# ========================================

def send_to_ra8p1(category):

    # RA8P1 current C parser expects
    # category only: FIRE / MEDICAL / ROAD / NORMAL

    payload = category.encode("ascii")

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
    print("Ethernet Category :", category)

    sendp(
        packet,
        iface=INTERFACE,
        verbose=True
    )

    print("Packet sent successfully.")


# ========================================
# PHONE HOME PAGE
# ========================================

@app.route("/")
def home():

    return """
    <!DOCTYPE html>

    <html>

    <head>

        <meta name="viewport"
              content="width=device-width, initial-scale=1.0">

        <title>Disaster Report</title>

        <style>

            body {
                font-family: Arial, sans-serif;
                text-align: center;
                padding: 25px;
                background: #f4f6f8;
            }

            h2 {
                color: #b00020;
            }

            textarea {
                width: 90%;
                max-width: 450px;
                padding: 12px;
                font-size: 17px;
                border-radius: 8px;
                border: 1px solid #aaa;
            }

            button {
                margin-top: 15px;
                padding: 14px 30px;
                font-size: 18px;
                font-weight: bold;
                border: none;
                border-radius: 8px;
                background: #d32f2f;
                color: white;
            }

        </style>

    </head>

    <body>

        <h2>🚨 Disaster Report</h2>

        <p>Describe what happened:</p>

        <form method="POST" action="/report">

            <textarea
                name="message"
                rows="6"
                placeholder="Example: There is a fire in my building..."
                required></textarea>

            <br>

            <button type="submit">
                SEND ALERT
            </button>

        </form>

    </body>

    </html>
    """


# ========================================
# RECEIVE DISASTER REPORT
# ========================================

@app.route("/report", methods=["POST"])
def report():

    message = request.form["message"]

    # AI classification
    category = classify_disaster(message)


    # ====================================
    # PRIORITY MAPPING
    # ====================================

    if category == "FIRE":
        priority = 1

    elif category == "MEDICAL":
        priority = 2

    elif category == "ROAD":
        priority = 3

    else:
        priority = 4


    # ====================================
    # DISPLAY RESULT ON PC
    # ====================================

    print("\n========================================")
    print("       DISASTER REPORT RECEIVED")
    print("========================================")

    print("Message  :", message)
    print("Category :", category)
    print("Priority :", priority)


    # ====================================
    # SEND TO RA8P1
    # ====================================

    send_to_ra8p1(category)

    print("========================================")


    # ====================================
    # RESPONSE TO PHONE
    # ====================================

    return f"""
    <!DOCTYPE html>

    <html>

    <head>

        <meta name="viewport"
              content="width=device-width, initial-scale=1.0">

        <title>Alert Sent</title>

    </head>

    <body style="text-align:center;
                 font-family:Arial;
                 padding:30px;">

        <h2>✅ Alert Sent</h2>

        <p><b>Detected Category:</b></p>

        <h1>{category}</h1>

        <p><b>Priority:</b> {priority}</p>

        <p>Alert forwarded to disaster communication system.</p>

        <br>

        <a href="/">
            Send another report
        </a>

    </body>

    </html>
    """


# ========================================
# START SERVER
# ========================================

if __name__ == "__main__":

    app.run(
        host="0.0.0.0",
        port=5000
    )