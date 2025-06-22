import pandas as pd
from data_loader import load_housing_data

def test_load_housing_data():
    df = load_housing_data()
    # Expect ~20k rows, 9 columns (8 features + target)
    assert isinstance(df, pd.DataFrame)
    assert df.shape[0] >= 20000
    expected_columns = {
        'MedInc', 'HouseAge', 'AveRooms', 'AveBedrms',
        'Population', 'AveOccup', 'Latitude', 'Longitude',
        'MedHouseVal'
    }
    assert set(df.columns) == expected_columns
