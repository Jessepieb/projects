import smtplib
import nmap

file = open("input.txt")
creds = file.readlines()
sent_from = creds[0]
to = [creds[0]]
nmScan = nmap.PortScanner()
subject = "Testmail"
nmScan.scan(hosts='192.168.192.1/24', arguments='-sn')
for host in nmScan.all_hosts():
    msg += str(host)
email_text= """\
From: %s
To: %s
Subject: %s

%s
""" % (sent_from,", ".join(to), subject, str(msg))
try:
    server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
    server.ehlo()
    server.login(creds[0], creds[1])
    server.sendmail(sent_from, to, email_text)
    server.close()
except:
    print("somthing went wrong")

file.close()
