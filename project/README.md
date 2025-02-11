# Google Sheets Automation with Up-to-Date Web Information (Practical Application)
#### Video Demo:  [<https://youtu.be/geNl7DbiMTE>]
#### Description:

I created this automation based on a real need at my workplace.

In the state of Paraná (Brazil), we use a government system to handle processes with various documents between different units.

Due to the large volume of documents, it's common for us to use spreadsheets (Google Sheets or Excel) to track the progress of these processes. In my department, we work with agreements, and we need to know if these agreements are progressing or stalled in a specific unit, so that we can monitor and contact the responsible person.

However, these spreadsheets need to be updated regularly, and as the number of processes increases, the time it takes to check each process protocol number, verify its location, and determine how long it has been there takes up a considerable amount of time for the person responsible for this task.

That's why I created this automation, which accesses the spreadsheet through the user's Google account, copies the protocol number, pastes it into the public consultation page of the system (eProtocolo), finds the web page field where the information about the protocol's location and arrival date is displayed, copies this information, and pastes it into the corresponding field in the spreadsheet.

The way the code is constructed allows for easy editing for other specific needs, such as opening different spreadsheets and accessing information from other websites.

The code was written entirely in Google Colab because the company's computers have proxy and administrator restrictions. This also makes it easier for different people to use the code, as it can simply be shared, or copies of the Colab Notebook can be sent to anyone who needs to run the script.

First, we install and configure Selenium. Then, we set up and configure the Web Driver. Remember that the code written here refers to the version of Google Colab, for use on multiple machines.

Next, we execute user authentication to use the credentials logged into the browser (Chrome) to access Google Sheets, allowing us to locate the spreadsheet that will be opened for automation. This authentication method allows different users to use the same automation and increases security since no user information is directly written into the code.

The spreadsheet is identified by its name and stored in a variable.

After that, the main code begins, consisting of a for loop that will go through all the rows of the spreadsheet.

For each row, the code will copy the protocol number by indicating which cell it is in, open the public search page of the system, paste the information in the respective area, and click the search button.

Here and in the previous step, when opening the system's consultation page, there is a while loop that checks every 0.3 seconds if the page has loaded, thus preventing errors related to waiting time. If we set a fixed time, it might be too long, making the automation slower than necessary, or too short, causing errors by attempting to execute the next steps before the page has fully loaded. In this way, the execution time of the code will be proportional to the quality of the internet signal, taking only the necessary time for the page to load, making the code more efficient.

Next, after the page has fully loaded, the automation will locate the information we need and store it in their respective variables in text format, to then update this information in the spreadsheet in the corresponding cells indicated in the code.
