"""
Website summarizer using Ollama instead of OpenAI.
"""

from openai import OpenAI
import os
from dotenv import load_dotenv
from scraper import fetch_website_contents
load_dotenv(override=True)



system_prompt = """
You are a snarky assistant that analyzes the contents of a website,
and provides a short, snarky, humorous summary, ignoring text that might be navigation related.
Respond in markdown. Do not wrap the markdown in a code block - respond just with the markdown.
"""

user_prompt_prefix = """
Here are the contents of a website.
Provide a short summary of this website.
If it includes news or announcements, then summarize these too.

"""


def messages_for(website):
    """Create message list for the LLM."""
    return [
        {"role": "system", "content": system_prompt},
        {"role": "user", "content": user_prompt_prefix + website}
    ]


def summarize(url):
    """Fetch and summarize a website using Ollama."""
    ollama = OpenAI(base_url="https://ollama.com/v1", api_key=os.environ.get("OLLAMA_API_KEY"))
    website = fetch_website_contents(url)
    response = ollama.chat.completions.create(
        model="gemma3:4b",
        messages=messages_for(website)
    )
    return response.choices[0].message.content


def main():
    """Main entry point for testing."""
    url = input("Enter a URL to summarize: ")
    print("\nFetching and summarizing...\n")
    summary = summarize(url)
    print(summary)


if __name__ == "__main__":
    main()
