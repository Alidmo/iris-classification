from sklearn.datasets import fetch_california_housing
import pandas as pd

def load_housing_data() -> pd.DataFrame:
    """
    Fetch California Housing data and return as DataFrame,
    features + 'MedHouseVal' target.
    """
    data = fetch_california_housing(as_frame=True)
    df = data.frame.copy()
    # rename target column for clarity
    df = df.rename(columns={'MedHouseVal': 'MedHouseVal'})
    return df
