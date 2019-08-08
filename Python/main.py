import smtplib
import nmap

file = open("input.txt")
creds = file.readlines()
sent_from = creds[0]
to = [creds[0]]
print("starting port scanner...")
nmScan = nmap.PortScanner()
print("Portscanner Started...")
subject = "Testmail"
msg = """"""
print("starting scan...")
nmScan.scan(hosts='192.168.192.1/24', arguments=' -sn -v')
print('Results'.center(20, '-'))
print(nmScan.csv())
for host in nmScan.all_hosts():
    msg += str(host)
    #msg += str(nmScan[host].get())
email_text= """\
From: %s
To: %s
Subject: %s

%s
""" % (sent_from,", ".join(to), subject, msg)
try:
    server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
    server.ehlo()
    server.login(creds[0], creds[1])
    server.sendmail(sent_from, to, email_text)
    server.close()
except:
    print("somthing went wrong")


file.close()