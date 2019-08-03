import smtplib
import nmap

file = open("input.txt")

creds = file.readlines()
sent_from = creds[0]
to = [creds[0]]
nmScan = nmap.PortScanner()
body = nmScan.scan('127.0.0.1', '21-443')
email_text= """\
%s
""" % (body)
try:
    server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
    server.ehlo()
    server.login(creds[0], creds[1])
    server.sendmail(sent_from, to, email_text)
    server.close()
except:
    print("somthing went wrong")

file.close()
