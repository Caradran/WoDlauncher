import discord
import subprocess
import sys, time
import re


TOKEN = 'NDc4OTkyNzIwMjU0NDY4MDk3.DlS2gg.7Hy76jvzPT-XNUtkibrEUE7DPSI'

client = discord.Client()

@client.event
async def on_message(message):
	if message.author == client.user:
		return
	if message.content.startswith('?(') or message.content.startswith('?r') or message.content.startswith('?roll'):
		print(message.content)
		cmd = "./wodices \"" + message.content +"\""
		print (cmd)
		process = subprocess.run([cmd],stdout=subprocess.PIPE,shell=True)
		
		msg = process.stdout.decode('utf-8')
		if len('{0.author.mention}\n'.format(message) + process.stdout.decode('utf-8')) < 2000 :
			await client.send_message(message.channel, '{0.author.mention}\n'.format(message) + msg)
		else :
			msg = re.search('resultat final.*[1-9]', msg) 
			await client.send_message(message.channel, '{0.author.mention}\n'.format(message) + msg.group(0))
		return 0

client.run(TOKEN)