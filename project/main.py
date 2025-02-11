'''The code was written 100% in Google Colab; this is the exact transcription of the file'''

# Install and configure Selenium

!pip install selenium

from selenium import webdriver

!apt-get update

!apt-get install chromium-driver

# Configure WebDriver

def web_driver():
    options = webdriver.ChromeOptions()
    options.add_argument("--verbose")
    options.add_argument('--no-sandbox')
    options.add_argument('--headless')
    options.add_argument('--disable-gpu')
    options.add_argument("--window-size=1920, 1200")
    options.add_argument('--disable-dev-usage')
    driver = webdriver.Chrome(options=options)
    return driver

driver = web_driver()

from selenium.webdriver.common.by import By
import time
from datetime import date

# Authenticate access to Google Sheets

from google.colab import auth
auth.authenticate_user()

import gspread
from google.auth import default
creds, _ = default()

gc = gspread.authorize(creds)

# Open the spreadsheet that will be used

worksheet = gc.open('Spreadsheet name').sheet1
rows = worksheet.get_all_values() # Assign the spreadsheet values to a list of lists in a variable (where each list is a row from the spreadsheet)

for i in range(1, len(rows)): # Go through all the filled rows of the spreadsheet
    protocol = rows[i][0] # Define which column and row the information is in
    driver.get('https://www.eprotocolo.pr.gov.br/spiweb/consultarProtocoloDigital.do?action=pesquisar') # Open the page in the browser created by Selenium
    while len(driver.find_elements(By.ID, 'numeroProtocolo')) < 1: # Wait for the page to load
        time.sleep(0.3)
    time.sleep(0.3)

    search = driver.find_element(By.ID, 'numeroProtocolo')
    search.send_keys(protocol) # Paste the information in the respective area of the site
    driver.find_element(By.ID, "btnPesquisar").click() # Click the button to search
    while len(driver.find_elements(By.XPATH, '//*[@id="UltimoAndamento_menos"]/div/table/tbody/tr[1]/td[4]')) < 1: # Wait for the page to load
        time.sleep(0.3)
    time.sleep(0.3)

    today = date.today().strftime('%d/%m/%Y') # Define the date for today (format used in Brazil)
    where = driver.find_element(By.XPATH, '//*[@id="UltimoAndamento_menos"]/div/table/tbody/tr[1]/td[4]').text # Copy the information in text format
    when = driver.find_element(By.XPATH, '//*[@id="UltimoAndamento_menos"]/div/table/tbody/tr[2]/td[4]').text # Copy the information in text format

    worksheet.update_acell(f'K{i+1}', today) # Update the information in the cell
    worksheet.update_acell(f'N{i+1}', where) # Update the information in the cell
    worksheet.update_acell(f'O{i+1}', when) # Update the information in the cell
