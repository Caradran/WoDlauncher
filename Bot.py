import discord
import subprocess
import sys, time
import re


TOKEN = ''

client = discord.Client()

@client.event
async def on_message(message):
	if message.author == client.user:
		return
	if message.content.startswith('?(') or message.content.startswith('?r(') or message.content.startswith('?roll('):
		print(message.content)
		cmd = "./wodices \"" + message.content +"\""
		print (cmd)
		msg_reg = re.search('.*[1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9].*', message.content)
		if (msg_reg) :
			await message.channel.send('{0.author.mention}\n'.format(message) + "stop messing with my bot !")
			return 0
		process = subprocess.run([cmd],stdout=subprocess.PIPE,shell=True)
		msg = process.stdout.decode('utf-8')
		print (msg)
		if len('{0.author.mention}\n'.format(message) + process.stdout.decode('utf-8')) < 2000 :
			await message.channel.send('{0.author.mention}\n'.format(message) + msg)
		else :
			msg = re.search('resultat final.*[0-9]', msg)
			if (msg) :
				await message.channel.send('{0.author.mention}\n'.format(message) + msg.group(0))
			else :
				await message.channel.send('{0.author.mention}\n'.format(message) + "stop messing with my bot !")

		return 0
	if message.content.startswith('?rodent'):
		print(message.content)
		msg = re.search('[1-9].*[0-9]', message.content)
		cmd = "./rodent " + msg.group(0)
		print (cmd)
		process = subprocess.run([cmd],stdout=subprocess.PIPE,shell=True)
		msg = process.stdout.decode('utf-8')
		print (msg)
		if len('{0.author.mention}\n'.format(message) + process.stdout.decode('utf-8')) < 2000 :
			await message.channel.send('{0.author.mention}\n'.format(message) + msg)
		return 0
	if message.content.startswith('?help'):
		await message.channel.send('{0.author.mention}\n'.format(message) + "usage : ?(nombre de dés, (optionnel) threshold des succès, (optionnel) threshold des reroll, (optionnel) nb de rotes)")
client.run(TOKEN)