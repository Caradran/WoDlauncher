from discord.ext.commands import Bot
from subprocess import run

TOKEN = 'NDc4OTkyNzIwMjU0NDY4MDk3.DlS2gg.7Hy76jvzPT-XNUtkibrEUE7DPSI'
BOT_PREFIX = {"+", "-"}


client = Bot(command_prefix=BOT_PREFIX)

@client.command(name='roll',)
async def roll(message):
	run(["./wodices", message, "to", "wodices"]);

    

client.run(TOKEN)