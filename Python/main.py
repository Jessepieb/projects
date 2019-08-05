import smtplib
import nmap


def getMacs(iprange):

    macs = open("macs.txt", "a+")
    nmScan = nmap.PortScanner()
    nmScan.scan(hosts=iprange, arguments='-sn')
    msg = ""
    for host in nmScan.all_hosts():
        if 'mac' in nmScan[host]['addresses']:
            msg += str(nmScan[host]['addresses']['ipv4']) + ' : ' + str(nmScan[host]['vendor'])
            if str(nmScan[host]['vendor']) not in macs:
                macs.write(str(nmScan[host]['vendor']) + '\n')
        msg += nmScan[host].hostname() + '\n '

    macs.close()
    return msg

def sendMail(body):

    file = open("input.txt")
    creds = file.readlines()
    sent_from = creds[0]
    to = [creds[0]]
    msg = body
    email_text = """\
    From: %s
    To: %s
    
    %s
    """ % (sent_from, ",".join(to), str(msg))

    message = """From: From Person <from@fromdomain.com>
    To: To Person <to@todomain.com>
    MIME-Version: 1.0
    Content-type: text/html
    Subject: SMTP HTML e-mail test

    This is an e-mail message to be sent in HTML format

    <b>This is HTML message.</b>
    <h1>This is headline.</h1>
    """
    try:
        server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
        server.ehlo()
        server.login(creds[0], creds[1])
        server.sendmail(sent_from, to, message)
        server.close()
    except:
        print("somthing went wrong")
    file.close()


def main():
    text = getMacs('192.168.192.1/24')
    sendMail(text)


main()