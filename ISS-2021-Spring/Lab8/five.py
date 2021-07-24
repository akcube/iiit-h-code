"""
Be careful while indenting the code.
Current indentation size: 4 spaces; no tab
"""
import random
import timeit
old_prices = [random.randrange(100) for _ in range(100000)]
def get_price(old_price):
    return old_price * 1.8


# ---Don't edit above this line-------
def get_prices_with_map():
    # logic goes here
    return list(map(get_price, old_prices))

def get_prices_with_comprehension():
    # logic goes here
    return [get_price(x) for x in old_prices]

def get_prices_with_loop():
    # logic goes here
    news = []
    for x in old_prices:
        news.append(get_price(x))
    return news

# ---Don't edit below this line-------


print("map function: ", timeit.timeit(get_prices_with_map, number=100))
print("comprehension: ",timeit.timeit(get_prices_with_comprehension, number=100))
print("for loop: ", timeit.timeit(get_prices_with_loop, number=100))